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

/* Variables and functions */
 int /*<<< orphan*/  CMD_IDU_READ_MODE ; 
 int /*<<< orphan*/  CMD_IDU_SET_MODE ; 
 int /*<<< orphan*/  __mcip_cmd_data (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int __mcip_cmd_read (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void idu_set_mode(unsigned int cmn_irq, bool set_lvl, unsigned int lvl,
			 bool set_distr, unsigned int distr)
{
	union {
		unsigned int word;
		struct {
			unsigned int distr:2, pad:2, lvl:1, pad2:27;
		};
	} data;

	data.word = __mcip_cmd_read(CMD_IDU_READ_MODE, cmn_irq);
	if (set_distr)
		data.distr = distr;
	if (set_lvl)
		data.lvl = lvl;
	__mcip_cmd_data(CMD_IDU_SET_MODE, cmn_irq, data.word);
}