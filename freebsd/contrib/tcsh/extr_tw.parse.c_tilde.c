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
struct Strbuf {int len; char* s; } ;
typedef  int Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int*) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int* Strnsave (int*,int) ; 
 int* gethdir (int*) ; 
 int* globequal (int*) ; 
 int /*<<< orphan*/  xfree (int*) ; 

__attribute__((used)) static int
tilde(struct Strbuf *new, Char *old)
{
    Char *o, *p;

    new->len = 0;
    switch (old[0]) {
    case '~': {
	Char *name, *home;

	old++;
	for (o = old; *o && *o != '/'; o++)
	    continue;
	name = Strnsave(old, o - old);
	home = gethdir(name);
	xfree(name);
	if (home == NULL)
	    goto err;
	Strbuf_append(new, home);
	xfree(home);
	/* If the home directory expands to "/", we do
	 * not want to create "//" by appending a slash from o.
	 */
	if (new->s[0] == '/' && new->len == 1 && *o == '/')
	    ++o;
	Strbuf_append(new, o);
	break;
    }

    case '=':
	if ((p = globequal(old)) == NULL)
	    goto err;
	if (p != old) {
	    Strbuf_append(new, p);
	    xfree(p);
	    break;
	}
	/*FALLTHROUGH*/

    default:
	Strbuf_append(new, old);
	break;
    }
    Strbuf_terminate(new);
    return 0;

 err:
    Strbuf_terminate(new);
    return -1;
}