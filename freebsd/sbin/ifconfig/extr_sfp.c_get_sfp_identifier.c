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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8472_BASE ; 
 int /*<<< orphan*/  SFF_8472_ID ; 
 int /*<<< orphan*/  convert_sff_identifier (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_sfp_identifier(struct i2c_info *ii, char *buf, size_t size)
{
	uint8_t data;

	read_i2c(ii, SFF_8472_BASE, SFF_8472_ID, 1, &data);
	convert_sff_identifier(buf, size, data);
}