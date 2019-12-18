#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  TYPE_1__ tokenstr_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AU_OFLAG_NONE ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int atf_utils_grep_string (char*,char*,char const*) ; 
 int au_fetch_tok (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  au_print_flags_tok (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int au_read_rec (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fmemopen (char*,int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static bool
get_records(const char *auditregex, FILE *pipestream)
{
	uint8_t *buff;
	tokenstr_t token;
	ssize_t size = 1024;
	char membuff[size];
	char del[] = ",";
	int reclen, bytes = 0;
	FILE *memstream;

	/*
	 * Open a stream on 'membuff' (address to memory buffer) for storing
	 * the audit records in the default mode.'reclen' is the length of the
	 * available records from auditpipe which is passed to the functions
	 * au_fetch_tok(3) and au_print_flags_tok(3) for further use.
	 */
	ATF_REQUIRE((memstream = fmemopen(membuff, size, "w")) != NULL);
	ATF_REQUIRE((reclen = au_read_rec(pipestream, &buff)) != -1);

	/*
	 * Iterate through each BSM token, extracting the bits that are
	 * required to start processing the token sequences.
	 */
	while (bytes < reclen) {
		if (au_fetch_tok(&token, buff + bytes, reclen - bytes) == -1) {
			perror("au_read_rec");
			atf_tc_fail("Incomplete Audit Record");
		}

		/* Print the tokens as they are obtained, in the default form */
		au_print_flags_tok(memstream, &token, del, AU_OFLAG_NONE);
		bytes += token.len;
	}

	free(buff);
	ATF_REQUIRE_EQ(0, fclose(memstream));
	return (atf_utils_grep_string("%s", membuff, auditregex));
}