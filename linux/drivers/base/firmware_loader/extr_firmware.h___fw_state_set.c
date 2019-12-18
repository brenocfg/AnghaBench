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
struct fw_state {int /*<<< orphan*/  completion; int /*<<< orphan*/  status; } ;
struct fw_priv {struct fw_state fw_st; } ;
typedef  enum fw_status { ____Placeholder_fw_status } fw_status ;

/* Variables and functions */
 int FW_STATUS_ABORTED ; 
 int FW_STATUS_DONE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __fw_state_set(struct fw_priv *fw_priv,
				  enum fw_status status)
{
	struct fw_state *fw_st = &fw_priv->fw_st;

	WRITE_ONCE(fw_st->status, status);

	if (status == FW_STATUS_DONE || status == FW_STATUS_ABORTED)
		complete_all(&fw_st->completion);
}