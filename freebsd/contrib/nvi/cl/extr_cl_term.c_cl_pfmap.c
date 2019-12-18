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
typedef  int /*<<< orphan*/  seq_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  L (char*) ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int SEQ_NOOVERWRITE ; 
 int SEQ_SCREEN ; 
 int /*<<< orphan*/  SIZE (int /*<<< orphan*/ *) ; 
 size_t SPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STRTOL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgq_wstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int seq_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* tigetstr (char*) ; 

__attribute__((used)) static int
cl_pfmap(SCR *sp, seq_t stype, CHAR_T *from, size_t flen, CHAR_T *to, size_t tlen)
{
	size_t nlen;
	char *p;
	char name[64];
	CHAR_T keyname[64];
	CHAR_T ts[20];
	CHAR_T *wp;
	size_t wlen;

	(void)snprintf(name, sizeof(name), "kf%d", 
			(int)STRTOL(from+1,NULL,10));
	if ((p = tigetstr(name)) == NULL ||
	    p == (char *)-1 || strlen(p) == 0)
		p = NULL;
	if (p == NULL) {
		msgq_wstr(sp, M_ERR, from, "233|This terminal has no %s key");
		return (1);
	}

	nlen = SPRINTF(keyname,
	    SIZE(keyname), L("function key %d"), 
			(int)STRTOL(from+1,NULL,10));
	CHAR2INT(sp, p, strlen(p), wp, wlen);
	MEMCPY(ts, wp, wlen);
	return (seq_set(sp, keyname, nlen,
	    ts, strlen(p), to, tlen, stype, SEQ_NOOVERWRITE | SEQ_SCREEN));
}