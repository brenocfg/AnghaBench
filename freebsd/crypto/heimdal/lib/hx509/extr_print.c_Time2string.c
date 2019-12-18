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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  Time ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _hx509_Time2time_t (int /*<<< orphan*/  const*) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int
Time2string(const Time *T, char **str)
{
    time_t t;
    char *s;
    struct tm *tm;

    *str = NULL;
    t = _hx509_Time2time_t(T);
    tm = gmtime (&t);
    s = malloc(30);
    if (s == NULL)
	return ENOMEM;
    strftime(s, 30, "%Y-%m-%d %H:%M:%S", tm);
    *str = s;
    return 0;
}