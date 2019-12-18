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
struct Strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  const Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_appendn (struct Strbuf*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  const* Strrchr (int /*<<< orphan*/  const*,char) ; 
 int /*<<< orphan*/  const* Strsave (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
extract_dir_and_name(const Char *path, struct Strbuf *dir, Char **name)
{
    Char *p;

    p = Strrchr(path, '/');
#ifdef WINNT_NATIVE
    if (p == NULL)
	p = Strrchr(path, ':');
#endif /* WINNT_NATIVE */
    if (p == NULL)
	*name = Strsave(path);
    else {
	p++;
	*name = Strsave(p);
	Strbuf_appendn(dir, path, p - path);
    }
    Strbuf_terminate(dir);
}