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
typedef  int /*<<< orphan*/  fn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/ * fopen (char*,char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 

__attribute__((used)) static FILE* myfopen(const char* filename, const char* mode)
{
	char* p;
	char fn[MAX_PATH];

	fn[0] = '\0';
	strncat(fn, filename, sizeof(fn)-1);

	for(p=fn;*p;++p) if(*p == '\\') *p = '/';

	return fopen(fn, mode);
}