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
typedef  int u8 ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int SHORT_ATOM_BYTESTRING ; 
 int SHORT_ATOM_ID ; 
 int SHORT_ATOM_LEN_MASK ; 
 int SHORT_ATOM_SIGNED ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 

__attribute__((used)) static void add_short_atom_header(struct opal_dev *cmd, bool bytestring,
				  bool has_sign, int len)
{
	u8 atom;
	int err = 0;

	atom = SHORT_ATOM_ID;
	atom |= bytestring ? SHORT_ATOM_BYTESTRING : 0;
	atom |= has_sign ? SHORT_ATOM_SIGNED : 0;
	atom |= len & SHORT_ATOM_LEN_MASK;

	add_token_u8(&err, cmd, atom);
}