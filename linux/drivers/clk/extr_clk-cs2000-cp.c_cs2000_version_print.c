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
struct device {int dummy; } ;
struct cs2000_priv {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ID ; 
 int EIO ; 
#define  REVISION_B2_B3 129 
#define  REVISION_C1 128 
 int REVISION_MASK ; 
 int cs2000_read (struct cs2000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*) ; 
 struct device* priv_to_dev (struct cs2000_priv*) ; 

__attribute__((used)) static int cs2000_version_print(struct cs2000_priv *priv)
{
	struct device *dev = priv_to_dev(priv);
	s32 val;
	const char *revision;

	val = cs2000_read(priv, DEVICE_ID);
	if (val < 0)
		return val;

	/* CS2000 should be 0x0 */
	if (val >> 3)
		return -EIO;

	switch (val & REVISION_MASK) {
	case REVISION_B2_B3:
		revision = "B2 / B3";
		break;
	case REVISION_C1:
		revision = "C1";
		break;
	default:
		return -EIO;
	}

	dev_info(dev, "revision - %s\n", revision);

	return 0;
}