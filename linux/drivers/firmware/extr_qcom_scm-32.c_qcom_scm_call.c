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
typedef  int u32 ;
struct qcom_scm_response {int /*<<< orphan*/  buf_offset; int /*<<< orphan*/  is_complete; } ;
struct qcom_scm_command {void* id; void* resp_hdr_offset; void* buf_offset; void* len; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ dma_map_single (struct device*,struct qcom_scm_command*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qcom_scm_command*) ; 
 struct qcom_scm_command* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qcom_scm_response* qcom_scm_command_to_response (struct qcom_scm_command*) ; 
 void* qcom_scm_get_command_buffer (struct qcom_scm_command*) ; 
 void const* qcom_scm_get_response_buffer (struct qcom_scm_response*) ; 
 int /*<<< orphan*/  qcom_scm_lock ; 
 int qcom_scm_remap_error (int) ; 
 int smc (scalar_t__) ; 

__attribute__((used)) static int qcom_scm_call(struct device *dev, u32 svc_id, u32 cmd_id,
			 const void *cmd_buf, size_t cmd_len, void *resp_buf,
			 size_t resp_len)
{
	int ret;
	struct qcom_scm_command *cmd;
	struct qcom_scm_response *rsp;
	size_t alloc_len = sizeof(*cmd) + cmd_len + sizeof(*rsp) + resp_len;
	dma_addr_t cmd_phys;

	cmd = kzalloc(PAGE_ALIGN(alloc_len), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->len = cpu_to_le32(alloc_len);
	cmd->buf_offset = cpu_to_le32(sizeof(*cmd));
	cmd->resp_hdr_offset = cpu_to_le32(sizeof(*cmd) + cmd_len);

	cmd->id = cpu_to_le32((svc_id << 10) | cmd_id);
	if (cmd_buf)
		memcpy(qcom_scm_get_command_buffer(cmd), cmd_buf, cmd_len);

	rsp = qcom_scm_command_to_response(cmd);

	cmd_phys = dma_map_single(dev, cmd, alloc_len, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, cmd_phys)) {
		kfree(cmd);
		return -ENOMEM;
	}

	mutex_lock(&qcom_scm_lock);
	ret = smc(cmd_phys);
	if (ret < 0)
		ret = qcom_scm_remap_error(ret);
	mutex_unlock(&qcom_scm_lock);
	if (ret)
		goto out;

	do {
		dma_sync_single_for_cpu(dev, cmd_phys + sizeof(*cmd) + cmd_len,
					sizeof(*rsp), DMA_FROM_DEVICE);
	} while (!rsp->is_complete);

	if (resp_buf) {
		dma_sync_single_for_cpu(dev, cmd_phys + sizeof(*cmd) + cmd_len +
					le32_to_cpu(rsp->buf_offset),
					resp_len, DMA_FROM_DEVICE);
		memcpy(resp_buf, qcom_scm_get_response_buffer(rsp),
		       resp_len);
	}
out:
	dma_unmap_single(dev, cmd_phys, alloc_len, DMA_TO_DEVICE);
	kfree(cmd);
	return ret;
}