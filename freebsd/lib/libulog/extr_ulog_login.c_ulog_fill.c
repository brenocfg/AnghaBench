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
struct utmpx {char* ut_line; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_pid; } ;
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  SHA1_Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
ulog_fill(struct utmpx *utx, const char *line)
{
	SHA_CTX c;
	char id[SHA_DIGEST_LENGTH];

	/* Remove /dev/ component. */
	if (strncmp(line, _PATH_DEV, sizeof _PATH_DEV - 1) == 0)
		line += sizeof _PATH_DEV - 1;

	memset(utx, 0, sizeof *utx);

	utx->ut_pid = getpid();
	gettimeofday(&utx->ut_tv, NULL);
	strncpy(utx->ut_line, line, sizeof utx->ut_line);

	SHA1_Init(&c);
	SHA1_Update(&c, "libulog", 7);
	SHA1_Update(&c, utx->ut_line, sizeof utx->ut_line);
	SHA1_Final(id, &c);

	memcpy(utx->ut_id, id, MIN(sizeof utx->ut_id, sizeof id));
}