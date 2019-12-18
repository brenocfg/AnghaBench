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
typedef  int /*<<< orphan*/  uintmax_t ;
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_3__ {char* name; int st_gid; int st_mode; int st_uid; char* md5digest; char* sha1digest; char* rmd160digest; char* sha256digest; int /*<<< orphan*/  st_flags; scalar_t__ st_size; scalar_t__ st_nlink; int /*<<< orphan*/  cksum; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 int F_CKSUM ; 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
 int F_MD5 ; 
 int F_MODE ; 
 int F_NLINK ; 
 int F_RMD160 ; 
 int F_SHA1 ; 
 int F_SHA256 ; 
 int F_SIZE ; 
 int F_UID ; 
 int F_UNAME ; 
 char* flags_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftype (int /*<<< orphan*/ ) ; 
 struct group* getgrgid (int) ; 
 struct passwd* getpwuid (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
shownode(NODE *n, int f, char const *path)
{
	struct group *gr;
	struct passwd *pw;

	printf("%s%s %s", path, n->name, ftype(n->type));
	if (f & F_CKSUM)
		printf(" cksum=%lu", n->cksum);
	if (f & F_GID)
		printf(" gid=%d", n->st_gid);
	if (f & F_GNAME) {
		gr = getgrgid(n->st_gid);
		if (gr == NULL)
			printf(" gid=%d", n->st_gid);
		else
			printf(" gname=%s", gr->gr_name);
	}
	if (f & F_MODE)
		printf(" mode=%o", n->st_mode);
	if (f & F_NLINK)
		printf(" nlink=%ju", (uintmax_t)n->st_nlink);
	if (f & F_SIZE)
		printf(" size=%jd", (intmax_t)n->st_size);
	if (f & F_UID)
		printf(" uid=%d", n->st_uid);
	if (f & F_UNAME) {
		pw = getpwuid(n->st_uid);
		if (pw == NULL)
			printf(" uid=%d", n->st_uid);
		else
			printf(" uname=%s", pw->pw_name);
	}
	if (f & F_MD5)
		printf(" md5digest=%s", n->md5digest);
	if (f & F_SHA1)
		printf(" sha1digest=%s", n->sha1digest);
	if (f & F_RMD160)
		printf(" rmd160digest=%s", n->rmd160digest);
	if (f & F_SHA256)
		printf(" sha256digest=%s", n->sha256digest);
	if (f & F_FLAGS)
		printf(" flags=%s", flags_to_string(n->st_flags));
	printf("\n");
}