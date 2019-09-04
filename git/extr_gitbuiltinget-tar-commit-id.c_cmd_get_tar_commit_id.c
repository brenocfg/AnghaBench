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
struct ustar_header {char* typeflag; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ GIT_HASH_UNKNOWN ; 
 int HEADERSIZE ; 
 int RECORDSIZE ; 
 int /*<<< orphan*/  builtin_get_tar_commit_id_usage ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ hash_algo_by_length (long) ; 
 scalar_t__ read_in_full (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  skip_prefix (char*,char*,char const**) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int,char const*,long) ; 

int cmd_get_tar_commit_id(int argc, const char **argv, const char *prefix)
{
	char buffer[HEADERSIZE];
	struct ustar_header *header = (struct ustar_header *)buffer;
	char *content = buffer + RECORDSIZE;
	const char *comment;
	ssize_t n;
	long len;
	char *end;

	if (argc != 1)
		usage(builtin_get_tar_commit_id_usage);

	n = read_in_full(0, buffer, HEADERSIZE);
	if (n < 0)
		die_errno("git get-tar-commit-id: read error");
	if (n != HEADERSIZE)
		die_errno("git get-tar-commit-id: EOF before reading tar header");
	if (header->typeflag[0] != 'g')
		return 1;

	len = strtol(content, &end, 10);
	if (errno == ERANGE || end == content || len < 0)
		return 1;
	if (!skip_prefix(end, " comment=", &comment))
		return 1;
	len -= comment - content;
	if (len < 1 || !(len % 2) ||
	    hash_algo_by_length((len - 1) / 2) == GIT_HASH_UNKNOWN)
		return 1;

	if (write_in_full(1, comment, len) < 0)
		die_errno("git get-tar-commit-id: write error");

	return 0;
}