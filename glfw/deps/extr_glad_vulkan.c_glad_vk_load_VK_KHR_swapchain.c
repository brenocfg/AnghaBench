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
typedef  scalar_t__ PFN_vkQueuePresentKHR ;
typedef  scalar_t__ PFN_vkGetSwapchainImagesKHR ;
typedef  scalar_t__ PFN_vkGetPhysicalDevicePresentRectanglesKHR ;
typedef  scalar_t__ PFN_vkGetDeviceGroupSurfacePresentModesKHR ;
typedef  scalar_t__ PFN_vkGetDeviceGroupPresentCapabilitiesKHR ;
typedef  scalar_t__ PFN_vkDestroySwapchainKHR ;
typedef  scalar_t__ PFN_vkCreateSwapchainKHR ;
typedef  scalar_t__ PFN_vkAcquireNextImageKHR ;
typedef  scalar_t__ PFN_vkAcquireNextImage2KHR ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_VK_KHR_swapchain ; 
 scalar_t__ vkAcquireNextImage2KHR ; 
 scalar_t__ vkAcquireNextImageKHR ; 
 scalar_t__ vkCreateSwapchainKHR ; 
 scalar_t__ vkDestroySwapchainKHR ; 
 scalar_t__ vkGetDeviceGroupPresentCapabilitiesKHR ; 
 scalar_t__ vkGetDeviceGroupSurfacePresentModesKHR ; 
 scalar_t__ vkGetPhysicalDevicePresentRectanglesKHR ; 
 scalar_t__ vkGetSwapchainImagesKHR ; 
 scalar_t__ vkQueuePresentKHR ; 

__attribute__((used)) static void glad_vk_load_VK_KHR_swapchain( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_swapchain) return;
    vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR) load("vkAcquireNextImage2KHR", userptr);
    vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) load("vkAcquireNextImageKHR", userptr);
    vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) load("vkCreateSwapchainKHR", userptr);
    vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) load("vkDestroySwapchainKHR", userptr);
    vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR) load("vkGetDeviceGroupPresentCapabilitiesKHR", userptr);
    vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR) load("vkGetDeviceGroupSurfacePresentModesKHR", userptr);
    vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR) load("vkGetPhysicalDevicePresentRectanglesKHR", userptr);
    vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) load("vkGetSwapchainImagesKHR", userptr);
    vkQueuePresentKHR = (PFN_vkQueuePresentKHR) load("vkQueuePresentKHR", userptr);
}