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

/* Variables and functions */
 char* GO_VERSION ; 
 char* INFO_MORE_INFO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void
display_version (void)
{
  fprintf (stdout, "GoAccess - %s.\n", GO_VERSION);
  fprintf (stdout, "%s: http://goaccess.io\n", INFO_MORE_INFO);
  fprintf (stdout, "Copyright (C) 2009-2016 by Gerardo Orellana\n");
  fprintf (stdout, "\nBuild configure arguments:\n");
#ifdef DEBUG
  fprintf (stdout, "  --enable-debug\n");
#endif
#ifdef HAVE_NCURSESW_NCURSES_H
  fprintf (stdout, "  --enable-utf8\n");
#endif
#ifdef HAVE_LIBGEOIP
  fprintf (stdout, "  --enable-geoip=legacy\n");
#endif
#ifdef HAVE_LIBMAXMINDDB
  fprintf (stdout, "  --enable-geoip=mmdb\n");
#endif
#ifdef TCB_MEMHASH
  fprintf (stdout, "  --enable-tcb=memhash\n");
#endif
#ifdef TCB_BTREE
  fprintf (stdout, "  --enable-tcb=btree\n");
#endif
#if defined(TCB_MEMHASH) || defined(TCB_BTREE)
#ifndef HAVE_ZLIB
  fprintf (stdout, "  --disable-zlib\n");
#endif
#ifndef HAVE_BZ2
  fprintf (stdout, "  --disable-bzip\n");
#endif
#endif
#ifdef WITH_GETLINE
  fprintf (stdout, "  --with-getline\n");
#endif
#ifdef HAVE_LIBSSL
  fprintf (stdout, "  --with-openssl\n");
#endif
}