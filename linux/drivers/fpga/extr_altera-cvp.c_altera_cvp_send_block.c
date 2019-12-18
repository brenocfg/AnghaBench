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
typedef  int u32 ;
struct altera_cvp_conf {int /*<<< orphan*/  (* write_data ) (struct altera_cvp_conf*,int const) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  stub1 (struct altera_cvp_conf*,int const) ; 
 int /*<<< orphan*/  stub2 (struct altera_cvp_conf*,int const) ; 

__attribute__((used)) static int altera_cvp_send_block(struct altera_cvp_conf *conf,
				 const u32 *data, size_t len)
{
	u32 mask, words = len / sizeof(u32);
	int i, remainder;

	for (i = 0; i < words; i++)
		conf->write_data(conf, *data++);

	/* write up to 3 trailing bytes, if any */
	remainder = len % sizeof(u32);
	if (remainder) {
		mask = BIT(remainder * 8) - 1;
		if (mask)
			conf->write_data(conf, *data & mask);
	}

	return 0;
}