#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct signature_check {char* gpg_status; char result; void* key; void* signer; void* fingerprint; void* primary_key_fingerprint; } ;
struct TYPE_3__ {char* check; int flags; char result; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FREE_AND_NULL (void*) ; 
 int GPG_STATUS_EXCLUSIVE ; 
 int GPG_STATUS_FINGERPRINT ; 
 int GPG_STATUS_KEYID ; 
 int GPG_STATUS_UID ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_1__* sigcheck_gpg_status ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 char* strchrnul (char const*,char) ; 
 void* xmemdupz (char const*,int) ; 

__attribute__((used)) static void parse_gpg_output(struct signature_check *sigc)
{
	const char *buf = sigc->gpg_status;
	const char *line, *next;
	int i, j;
	int seen_exclusive_status = 0;

	/* Iterate over all lines */
	for (line = buf; *line; line = strchrnul(line+1, '\n')) {
		while (*line == '\n')
			line++;
		if (!*line)
			break;

		/* Skip lines that don't start with GNUPG status */
		if (!skip_prefix(line, "[GNUPG:] ", &line))
			continue;

		/* Iterate over all search strings */
		for (i = 0; i < ARRAY_SIZE(sigcheck_gpg_status); i++) {
			if (skip_prefix(line, sigcheck_gpg_status[i].check, &line)) {
				if (sigcheck_gpg_status[i].flags & GPG_STATUS_EXCLUSIVE) {
					if (seen_exclusive_status++)
						goto found_duplicate_status;
				}

				if (sigcheck_gpg_status[i].result)
					sigc->result = sigcheck_gpg_status[i].result;
				/* Do we have key information? */
				if (sigcheck_gpg_status[i].flags & GPG_STATUS_KEYID) {
					next = strchrnul(line, ' ');
					free(sigc->key);
					sigc->key = xmemdupz(line, next - line);
					/* Do we have signer information? */
					if (*next && (sigcheck_gpg_status[i].flags & GPG_STATUS_UID)) {
						line = next + 1;
						next = strchrnul(line, '\n');
						free(sigc->signer);
						sigc->signer = xmemdupz(line, next - line);
					}
				}
				/* Do we have fingerprint? */
				if (sigcheck_gpg_status[i].flags & GPG_STATUS_FINGERPRINT) {
					next = strchrnul(line, ' ');
					free(sigc->fingerprint);
					sigc->fingerprint = xmemdupz(line, next - line);

					/* Skip interim fields */
					for (j = 9; j > 0; j--) {
						if (!*next)
							break;
						line = next + 1;
						next = strchrnul(line, ' ');
					}

					next = strchrnul(line, '\n');
					free(sigc->primary_key_fingerprint);
					sigc->primary_key_fingerprint = xmemdupz(line, next - line);
				}

				break;
			}
		}
	}
	return;

found_duplicate_status:
	/*
	 * GOODSIG, BADSIG etc. can occur only once for each signature.
	 * Therefore, if we had more than one then we're dealing with multiple
	 * signatures.  We don't support them currently, and they're rather
	 * hard to create, so something is likely fishy and we should reject
	 * them altogether.
	 */
	sigc->result = 'E';
	/* Clear partial data to avoid confusion */
	FREE_AND_NULL(sigc->primary_key_fingerprint);
	FREE_AND_NULL(sigc->fingerprint);
	FREE_AND_NULL(sigc->signer);
	FREE_AND_NULL(sigc->key);
}