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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror_r (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void warnvf(const char *fmt, va_list args)
{
    char errbuf[256];

    if (errno != 0) {
        strerror_r(errno, errbuf, sizeof(errbuf));
    } else {
        errbuf[0] = '\0';
    }

    fprintf(stderr, "[openssl-privsep] ");
    vfprintf(stderr, fmt, args);
    if (errbuf[0] != '\0')
        fputs(errbuf, stderr);
    fputc('\n', stderr);
}