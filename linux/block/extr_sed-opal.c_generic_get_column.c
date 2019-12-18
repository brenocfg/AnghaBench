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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ENDCOLUMN ; 
 int /*<<< orphan*/  OPAL_ENDLIST ; 
 int /*<<< orphan*/  OPAL_ENDNAME ; 
 size_t OPAL_GET ; 
 int /*<<< orphan*/  OPAL_STARTCOLUMN ; 
 int /*<<< orphan*/  OPAL_STARTLIST ; 
 int /*<<< orphan*/  OPAL_STARTNAME ; 
 int /*<<< orphan*/  add_token_u64 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int cmd_start (struct opal_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/  parse_and_check_status ; 

__attribute__((used)) static int generic_get_column(struct opal_dev *dev, const u8 *table,
			      u64 column)
{
	int err;

	err = cmd_start(dev, table, opalmethod[OPAL_GET]);

	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_STARTCOLUMN);
	add_token_u64(&err, dev, column);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_ENDCOLUMN);
	add_token_u64(&err, dev, column);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);

	if (err)
		return err;

	return finalize_and_send(dev, parse_and_check_status);
}