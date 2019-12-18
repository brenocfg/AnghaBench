#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teken_rect_t ;
typedef  int /*<<< orphan*/  teken_char_t ;
typedef  int /*<<< orphan*/  teken_attr_t ;
struct terminal {TYPE_1__* tm_class; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_fill ) (struct terminal*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TCHAR_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (struct terminal*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
termteken_fill(void *softc, const teken_rect_t *r, teken_char_t c,
    const teken_attr_t *a)
{
	struct terminal *tm = softc;

	tm->tm_class->tc_fill(tm, r, TCHAR_CREATE(c, a));
}