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
struct hstate {char const** seen; char* list; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_do_all_sorted (int /*<<< orphan*/ ,struct hstate*) ; 
 int /*<<< orphan*/  INIT_SSL () ; 
 int /*<<< orphan*/  K_PER_LINE ; 
 scalar_t__ emalloc (int) ; 
 scalar_t__ emalloc_zero (int) ; 
 int /*<<< orphan*/  free (char const**) ; 
 char* insert_cmac (char*) ; 
 int /*<<< orphan*/  list_md_fn ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
list_digest_names(void)
{
	char *list = NULL;
	
#ifdef OPENSSL
# ifdef HAVE_EVP_MD_DO_ALL_SORTED
	struct hstate hstate = { NULL, NULL, K_PER_LINE+1 };
	
	/* replace calloc(1, sizeof(const char *)) */
	hstate.seen = (const char **)emalloc_zero(sizeof(const char *));
	
	INIT_SSL();
	EVP_MD_do_all_sorted(list_md_fn, &hstate);
	list = hstate.list;
	free(hstate.seen);
	
	list = insert_cmac(list);	/* Insert CMAC into SSL digests list */
	
# else
	list = (char *)emalloc(sizeof("md5, others (upgrade to OpenSSL-1.0 for full list)"));
	strcpy(list, "md5, others (upgrade to OpenSSL-1.0 for full list)");
# endif
#else
	list = (char *)emalloc(sizeof("md5"));
	strcpy(list, "md5");
#endif
	
	return list;
}