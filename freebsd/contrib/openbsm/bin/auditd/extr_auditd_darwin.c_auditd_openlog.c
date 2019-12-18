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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILTER_MASK_UPTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_KEY_READ_GID ; 
 int /*<<< orphan*/  ASL_KEY_READ_UID ; 
 int /*<<< orphan*/  ASL_LEVEL_DEBUG ; 
 int /*<<< orphan*/  ASL_LEVEL_INFO ; 
 int /*<<< orphan*/  ASL_OPT_STDERR ; 
 int /*<<< orphan*/  ASL_TYPE_MSG ; 
 int /*<<< orphan*/  asl_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asl_open (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  asl_set_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_aslclient ; 
 int /*<<< orphan*/  au_aslmsg ; 
 int /*<<< orphan*/  free (char*) ; 

void
auditd_openlog(int debug, gid_t gid)
{
	uint32_t opt = 0;	
	char *cp = NULL;

	if (debug)
		opt = ASL_OPT_STDERR;

	au_aslclient = asl_open("auditd", "com.apple.auditd", opt);
	au_aslmsg = asl_new(ASL_TYPE_MSG); 

#ifdef ASL_KEY_READ_UID
	/*
	 * Make it only so the audit administrator and members of the audit
	 * review group (if used) have access to the auditd system log messages.
	 */
	asl_set(au_aslmsg, ASL_KEY_READ_UID, "0");
	asprintf(&cp, "%u", gid);	
	if (cp != NULL) {
#ifdef ASL_KEY_READ_GID
		asl_set(au_aslmsg, ASL_KEY_READ_GID, cp);
#endif
		free(cp);
	}
#endif

	/*
	 * Set the client-side system log filtering.
	 */
	if (debug)
		asl_set_filter(au_aslclient,
		    ASL_FILTER_MASK_UPTO(ASL_LEVEL_DEBUG));
	else
		asl_set_filter(au_aslclient,
		    ASL_FILTER_MASK_UPTO(ASL_LEVEL_INFO)); 	
}