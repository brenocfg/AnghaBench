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
struct fw_state {int status; } ;
struct fw_priv {struct fw_state fw_st; } ;
typedef  enum fw_status { ____Placeholder_fw_status } fw_status ;

/* Variables and functions */

__attribute__((used)) static inline bool __fw_state_check(struct fw_priv *fw_priv,
				    enum fw_status status)
{
	struct fw_state *fw_st = &fw_priv->fw_st;

	return fw_st->status == status;
}