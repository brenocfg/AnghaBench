#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct known_hosts_ctx {int found_key; char* host; int invalid; int /*<<< orphan*/  out; } ;
struct hostkey_foreach_line {scalar_t__ status; scalar_t__ marker; char* line; int /*<<< orphan*/  linenum; int /*<<< orphan*/  path; int /*<<< orphan*/  comment; int /*<<< orphan*/  key; } ;
typedef  enum sshkey_fp_rep { ____Placeholder_sshkey_fp_rep } sshkey_fp_rep ;

/* Variables and functions */
 scalar_t__ HKF_STATUS_INVALID ; 
 scalar_t__ HKF_STATUS_MATCHED ; 
 scalar_t__ MRK_CA ; 
 scalar_t__ MRK_NONE ; 
 scalar_t__ MRK_REVOKE ; 
 int SSH_DIGEST_SHA1 ; 
 int SSH_FP_BUBBLEBABBLE ; 
 int SSH_FP_DEFAULT ; 
 scalar_t__ delete_host ; 
 scalar_t__ find_host ; 
 int fingerprint_hash ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hash_hosts ; 
 int /*<<< orphan*/  known_hosts_hash (struct hostkey_foreach_line*,struct known_hosts_ctx*) ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprintf (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ print_bubblebabble ; 
 scalar_t__ print_fingerprint ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  quiet ; 
 char* sshkey_fingerprint (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sshkey_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
known_hosts_find_delete(struct hostkey_foreach_line *l, void *_ctx)
{
	struct known_hosts_ctx *ctx = (struct known_hosts_ctx *)_ctx;
	enum sshkey_fp_rep rep;
	int fptype;
	char *fp;

	fptype = print_bubblebabble ? SSH_DIGEST_SHA1 : fingerprint_hash;
	rep =    print_bubblebabble ? SSH_FP_BUBBLEBABBLE : SSH_FP_DEFAULT;

	if (l->status == HKF_STATUS_MATCHED) {
		if (delete_host) {
			if (l->marker != MRK_NONE) {
				/* Don't remove CA and revocation lines */
				fprintf(ctx->out, "%s\n", l->line);
			} else {
				/*
				 * Hostname matches and has no CA/revoke
				 * marker, delete it by *not* writing the
				 * line to ctx->out.
				 */
				ctx->found_key = 1;
				if (!quiet)
					printf("# Host %s found: line %lu\n",
					    ctx->host, l->linenum);
			}
			return 0;
		} else if (find_host) {
			ctx->found_key = 1;
			if (!quiet) {
				printf("# Host %s found: line %lu %s\n",
				    ctx->host,
				    l->linenum, l->marker == MRK_CA ? "CA" :
				    (l->marker == MRK_REVOKE ? "REVOKED" : ""));
			}
			if (hash_hosts)
				known_hosts_hash(l, ctx);
			else if (print_fingerprint) {
				fp = sshkey_fingerprint(l->key, fptype, rep);
				mprintf("%s %s %s %s\n", ctx->host,
				    sshkey_type(l->key), fp, l->comment);
				free(fp);
			} else
				fprintf(ctx->out, "%s\n", l->line);
			return 0;
		}
	} else if (delete_host) {
		/* Retain non-matching hosts when deleting */
		if (l->status == HKF_STATUS_INVALID) {
			ctx->invalid = 1;
			logit("%s:%lu: invalid line", l->path, l->linenum);
		}
		fprintf(ctx->out, "%s\n", l->line);
	}
	return 0;
}