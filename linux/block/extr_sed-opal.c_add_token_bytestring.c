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
struct opal_dev {size_t pos; } ;

/* Variables and functions */
 int /*<<< orphan*/ * add_bytestring_header (int*,struct opal_dev*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void add_token_bytestring(int *err, struct opal_dev *cmd,
				 const u8 *bytestring, size_t len)
{
	u8 *start;

	start = add_bytestring_header(err, cmd, len);
	if (!start)
		return;
	memcpy(start, bytestring, len);
	cmd->pos += len;
}