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
struct opal_key {int /*<<< orphan*/  key_len; int /*<<< orphan*/  const* key; } ;
struct opal_dev {int /*<<< orphan*/ * prev_data; int /*<<< orphan*/  prev_d_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ADMINSP_UID ; 
 int /*<<< orphan*/  OPAL_SID_UID ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/  const*) ; 
 int start_generic_opal_session (struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_SIDASP_opal_session(struct opal_dev *dev, void *data)
{
	int ret;
	const u8 *key = dev->prev_data;

	if (!key) {
		const struct opal_key *okey = data;

		ret = start_generic_opal_session(dev, OPAL_SID_UID,
						 OPAL_ADMINSP_UID,
						 okey->key,
						 okey->key_len);
	} else {
		ret = start_generic_opal_session(dev, OPAL_SID_UID,
						 OPAL_ADMINSP_UID,
						 key, dev->prev_d_len);
		kfree(key);
		dev->prev_data = NULL;
	}

	return ret;
}