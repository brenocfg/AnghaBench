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
struct nv {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  nv_add (struct nv*,unsigned char const*,size_t,int,char*) ; 
 size_t vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv_addv(struct nv *nv, const unsigned char *value, size_t vsize, int type,
    const char *namefmt, va_list nameap)
{
	char name[255];
	size_t namesize;

	namesize = vsnprintf(name, sizeof(name), namefmt, nameap);
	PJDLOG_ASSERT(namesize > 0 && namesize < sizeof(name));

	nv_add(nv, value, vsize, type, name);
}