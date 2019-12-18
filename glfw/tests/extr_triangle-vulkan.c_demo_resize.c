#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  image; int /*<<< orphan*/  view; } ;
struct TYPE_6__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  buf; } ;
struct demo {size_t swapchainImageCount; TYPE_4__* buffers; TYPE_3__ depth; int /*<<< orphan*/  device; TYPE_2__* textures; TYPE_1__ vertices; int /*<<< orphan*/  desc_layout; int /*<<< orphan*/  pipeline_layout; int /*<<< orphan*/  render_pass; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  cmd_pool; scalar_t__ draw_cmd; scalar_t__ setup_cmd; int /*<<< orphan*/  desc_pool; TYPE_4__* framebuffers; } ;
struct TYPE_9__ {int /*<<< orphan*/  view; } ;
struct TYPE_7__ {int /*<<< orphan*/  sampler; int /*<<< orphan*/  mem; int /*<<< orphan*/  image; int /*<<< orphan*/  view; } ;

/* Variables and functions */
 size_t DEMO_TEXTURE_COUNT ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  demo_prepare (struct demo*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  vkDestroyBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyCommandPool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyDescriptorPool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyDescriptorSetLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyFramebuffer (int /*<<< orphan*/ ,TYPE_4__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyImageView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyPipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyPipelineLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyRenderPass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroySampler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkFreeCommandBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vkFreeMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void demo_resize(struct demo *demo) {
    uint32_t i;

    // In order to properly resize the window, we must re-create the swapchain
    // AND redo the command buffers, etc.
    //
    // First, perform part of the demo_cleanup() function:

    for (i = 0; i < demo->swapchainImageCount; i++) {
        vkDestroyFramebuffer(demo->device, demo->framebuffers[i], NULL);
    }
    free(demo->framebuffers);
    vkDestroyDescriptorPool(demo->device, demo->desc_pool, NULL);

    if (demo->setup_cmd) {
        vkFreeCommandBuffers(demo->device, demo->cmd_pool, 1, &demo->setup_cmd);
        demo->setup_cmd = VK_NULL_HANDLE;
    }
    vkFreeCommandBuffers(demo->device, demo->cmd_pool, 1, &demo->draw_cmd);
    vkDestroyCommandPool(demo->device, demo->cmd_pool, NULL);

    vkDestroyPipeline(demo->device, demo->pipeline, NULL);
    vkDestroyRenderPass(demo->device, demo->render_pass, NULL);
    vkDestroyPipelineLayout(demo->device, demo->pipeline_layout, NULL);
    vkDestroyDescriptorSetLayout(demo->device, demo->desc_layout, NULL);

    vkDestroyBuffer(demo->device, demo->vertices.buf, NULL);
    vkFreeMemory(demo->device, demo->vertices.mem, NULL);

    for (i = 0; i < DEMO_TEXTURE_COUNT; i++) {
        vkDestroyImageView(demo->device, demo->textures[i].view, NULL);
        vkDestroyImage(demo->device, demo->textures[i].image, NULL);
        vkFreeMemory(demo->device, demo->textures[i].mem, NULL);
        vkDestroySampler(demo->device, demo->textures[i].sampler, NULL);
    }

    for (i = 0; i < demo->swapchainImageCount; i++) {
        vkDestroyImageView(demo->device, demo->buffers[i].view, NULL);
    }

    vkDestroyImageView(demo->device, demo->depth.view, NULL);
    vkDestroyImage(demo->device, demo->depth.image, NULL);
    vkFreeMemory(demo->device, demo->depth.mem, NULL);

    free(demo->buffers);

    // Second, re-perform the demo_prepare() function, which will re-create the
    // swapchain:
    demo_prepare(demo);
}