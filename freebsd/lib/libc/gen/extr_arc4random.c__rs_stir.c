#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  rnd ;
struct TYPE_4__ {int rs_count; scalar_t__ rs_have; } ;
struct TYPE_3__ {int /*<<< orphan*/  rs_buf; } ;

/* Variables and functions */
 int IVSZ ; 
 int KEYSZ ; 
 int /*<<< orphan*/  _getentropy_fail () ; 
 int /*<<< orphan*/  _rs_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rs_rekey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int getentropy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* rs ; 
 TYPE_1__* rsx ; 

__attribute__((used)) static void
_rs_stir(void)
{
	u_char rnd[KEYSZ + IVSZ];

	if (getentropy(rnd, sizeof rnd) == -1)
		_getentropy_fail();

	if (!rs)
		_rs_init(rnd, sizeof(rnd));
	else
		_rs_rekey(rnd, sizeof(rnd));
	explicit_bzero(rnd, sizeof(rnd));	/* discard source seed */

	/* invalidate rs_buf */
	rs->rs_have = 0;
	memset(rsx->rs_buf, 0, sizeof(rsx->rs_buf));

	rs->rs_count = 1600000;
}