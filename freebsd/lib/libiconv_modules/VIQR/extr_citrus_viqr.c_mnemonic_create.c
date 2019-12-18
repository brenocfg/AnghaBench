#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {int ascii; int /*<<< orphan*/  child; int /*<<< orphan*/  value; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ mnemonic_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static mnemonic_t *
mnemonic_create(mnemonic_t *parent, int ascii, wchar_t value)
{
	mnemonic_t *m;

	m = malloc(sizeof(*m));
	if (m != NULL) {
		m->parent = parent;
		m->ascii = ascii;
		m->value = value;
		TAILQ_INIT(&m->child);
	}

	return (m);
}