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
struct fw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_STATUS_ABORTED ; 
 int /*<<< orphan*/  __fw_state_set (struct fw_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fw_state_aborted(struct fw_priv *fw_priv)
{
	__fw_state_set(fw_priv, FW_STATUS_ABORTED);
}