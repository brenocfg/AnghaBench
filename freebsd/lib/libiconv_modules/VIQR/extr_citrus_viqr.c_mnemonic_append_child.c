#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int /*<<< orphan*/  value; int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ mnemonic_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 TYPE_1__* mnemonic_create (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mnemonic_list_find (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mnemonic_append_child(mnemonic_t *m, const char *s,
    wchar_t value, wchar_t invalid)
{
	mnemonic_t *m0;
	int ch;

	ch = (unsigned char)*s++;
	if (ch == '\0')
		return (EINVAL);
	m0 = mnemonic_list_find(&m->child, ch);
	if (m0 == NULL) {
		m0 = mnemonic_create(m, ch, (wchar_t)ch);
		if (m0 == NULL)
			return (ENOMEM);
		TAILQ_INSERT_TAIL(&m->child, m0, entry);
	}
	m = m0;
	for (m0 = NULL; (ch = (unsigned char)*s) != '\0'; ++s) {
		m0 = mnemonic_list_find(&m->child, ch);
		if (m0 == NULL) {
			m0 = mnemonic_create(m, ch, invalid);
			if (m0 == NULL)
				return (ENOMEM);
			TAILQ_INSERT_TAIL(&m->child, m0, entry);
		}
		m = m0;
	}
	if (m0 == NULL)
		return (EINVAL);
	m0->value = value;

	return (0);
}