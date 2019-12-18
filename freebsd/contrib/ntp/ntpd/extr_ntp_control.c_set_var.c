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
typedef  void* u_short ;
typedef  int /*<<< orphan*/  u_long ;
struct ctl_var {int flags; char* text; } ;

/* Variables and functions */
 int EOV ; 
 char* add_var (struct ctl_var**,int /*<<< orphan*/ ,void*) ; 
 char* emalloc (int /*<<< orphan*/ ) ; 
 char* erealloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 

void
set_var(
	struct ctl_var **kv,
	const char *data,
	u_long size,
	u_short def
	)
{
	struct ctl_var *k;
	const char *s;
	const char *t;
	char *td;

	if (NULL == data || !size)
		return;

	k = *kv;
	if (k != NULL) {
		while (!(EOV & k->flags)) {
			if (NULL == k->text)	{
				td = emalloc(size);
				memcpy(td, data, size);
				k->text = td;
				k->flags = def;
				return;
			} else {
				s = data;
				t = k->text;
				while (*t != '=' && *s == *t) {
					s++;
					t++;
				}
				if (*s == *t && ((*t == '=') || !*t)) {
					td = erealloc((void *)(intptr_t)k->text, size);
					memcpy(td, data, size);
					k->text = td;
					k->flags = def;
					return;
				}
			}
			k++;
		}
	}
	td = add_var(kv, size, def);
	memcpy(td, data, size);
}