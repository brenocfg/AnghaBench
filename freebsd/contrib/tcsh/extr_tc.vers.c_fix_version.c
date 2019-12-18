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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  AFSSTR ; 
 int /*<<< orphan*/  ALSTR ; 
 int /*<<< orphan*/  BYESTR ; 
 int /*<<< orphan*/  CCATSTR ; 
 int /*<<< orphan*/  COLORSTR ; 
 int /*<<< orphan*/  DATE ; 
 int /*<<< orphan*/  DLSTR ; 
 int /*<<< orphan*/  DSPMSTR ; 
 int /*<<< orphan*/  DTRSTR ; 
 int /*<<< orphan*/  FILECSTR ; 
 int /*<<< orphan*/  HBSTR ; 
 int /*<<< orphan*/  KANSTR ; 
 int /*<<< orphan*/  LFSTR ; 
 int /*<<< orphan*/  LOCALSTR ; 
 int /*<<< orphan*/  NDSTR ; 
 int /*<<< orphan*/  NGSTR ; 
 int /*<<< orphan*/  NLSSTR ; 
 int /*<<< orphan*/  ORIGIN ; 
 int /*<<< orphan*/  PATCHLEVEL ; 
 int /*<<< orphan*/  REV ; 
 int /*<<< orphan*/  RHSTR ; 
 int /*<<< orphan*/  SMSTR ; 
 int /*<<< orphan*/  SSSTR ; 
 int /*<<< orphan*/  STRMACHTYPE ; 
 int /*<<< orphan*/  STROSTYPE ; 
 int /*<<< orphan*/  STRVENDOR ; 
 int /*<<< orphan*/  STRtcsh ; 
 int /*<<< orphan*/ * STRunknown ; 
 int /*<<< orphan*/  STRversion ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  VERS ; 
 int /*<<< orphan*/  VISTR ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2short (char*) ; 
 int /*<<< orphan*/ * tgetenv (int /*<<< orphan*/ ) ; 
 char* xasprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xfree ; 

void
fix_version(void)
{
#ifdef WIDE_STRINGS
# define SSSTR "wide"
#elif defined (SHORT_STRINGS)
# define SSSTR "8b"
#else
# define SSSTR "7b"
#endif 
#ifdef NLS
# define NLSSTR ",nls"
#else
# define NLSSTR ""
#endif 
#ifdef LOGINFIRST
# define LFSTR ",lf"
#else
# define LFSTR ""
#endif 
#ifdef DOTLAST
# define DLSTR ",dl"
#else
# define DLSTR ""
#endif 
#ifdef VIDEFAULT
# define VISTR ",vi"
#else
# define VISTR ""
#endif 
#ifdef TESLA
# define DTRSTR ",dtr"
#else
# define DTRSTR ""
#endif 
#ifdef KAI
# define BYESTR ",bye"
#else
# define BYESTR ""
#endif 
#ifdef AUTOLOGOUT
# define ALSTR ",al"
#else
# define ALSTR ""
#endif 
#ifdef KANJI
# define KANSTR ",kan"
#else
# define KANSTR ""
#endif 
#ifdef SYSMALLOC
# define SMSTR	",sm"
#else
# define SMSTR  ""
#endif 
#ifdef HASHBANG
# define HBSTR	",hb"
#else
# define HBSTR  ""
#endif 
#ifdef NEWGRP
# define NGSTR	",ng"
#else
# define NGSTR	""
#endif
#ifdef REMOTEHOST
# define RHSTR	",rh"
#else
# define RHSTR	""
#endif
#ifdef AFS
# define AFSSTR	",afs"
#else
# define AFSSTR	""
#endif
#ifdef NODOT
# define NDSTR	",nd"
#else
# define NDSTR	""
#endif
#ifdef COLOR_LS_F
# define COLORSTR ",color"
#else /* ifndef COLOR_LS_F */
# define COLORSTR ""
#endif /* COLOR_LS_F */
#ifdef DSPMBYTE
# define DSPMSTR ",dspm"
#else
# define DSPMSTR ""
#endif
#ifdef COLORCAT
# define CCATSTR ",ccat"
#else
# define CCATSTR ""
#endif
#if defined(FILEC) && defined(TIOCSTI)
# define FILECSTR ",filec"
#else
# define FILECSTR ""
#endif
/* if you want your local version to say something */
#ifndef LOCALSTR
# define LOCALSTR ""
#endif /* LOCALSTR */
    char    *version;
    const Char *machtype = tgetenv(STRMACHTYPE);
    const Char *vendor   = tgetenv(STRVENDOR);
    const Char *ostype   = tgetenv(STROSTYPE);

    if (vendor == NULL)
	vendor = STRunknown;
    if (machtype == NULL)
	machtype = STRunknown;
    if (ostype == NULL)
	ostype = STRunknown;


    version = xasprintf(
"tcsh %d.%.2d.%.2d (%s) %s (%S-%S-%S) options %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
	     REV, VERS, PATCHLEVEL, ORIGIN, DATE, machtype, vendor, ostype,
	     SSSTR, NLSSTR, LFSTR, DLSTR, VISTR, DTRSTR, BYESTR,
	     ALSTR, KANSTR, SMSTR, HBSTR, NGSTR, RHSTR, AFSSTR, NDSTR,
	     COLORSTR, DSPMSTR, CCATSTR, FILECSTR, LOCALSTR);
    cleanup_push(version, xfree);
    setcopy(STRversion, str2short(version), VAR_READWRITE);
    cleanup_until(version);
    version = xasprintf("%d.%.2d.%.2d", REV, VERS, PATCHLEVEL);
    cleanup_push(version, xfree);
    setcopy(STRtcsh, str2short(version), VAR_READWRITE);
    cleanup_until(version);
}