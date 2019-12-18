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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int name_interpret (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * name_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
name_extract(netdissect_options *ndo,
             const u_char *buf, int ofs, const u_char *maxbuf, char *name)
{
    const u_char *p = name_ptr(ndo, buf, ofs, maxbuf);
    if (p == NULL)
	return(-1);	/* error (probably name going past end of buffer) */
    name[0] = '\0';
    return(name_interpret(ndo, p, maxbuf, name));
}