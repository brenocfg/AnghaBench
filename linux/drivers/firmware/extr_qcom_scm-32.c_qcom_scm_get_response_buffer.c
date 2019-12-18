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
struct qcom_scm_response {int /*<<< orphan*/  buf_offset; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *qcom_scm_get_response_buffer(const struct qcom_scm_response *rsp)
{
	return (void *)rsp + le32_to_cpu(rsp->buf_offset);
}