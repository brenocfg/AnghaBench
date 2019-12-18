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
typedef  scalar_t__ PFN_vkGetPhysicalDeviceSurfaceSupportKHR ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceSurfacePresentModesKHR ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceSurfaceFormatsKHR ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR ;
typedef  scalar_t__ PFN_vkDestroySurfaceKHR ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_VK_KHR_surface ; 
 scalar_t__ vkDestroySurfaceKHR ; 
 scalar_t__ vkGetPhysicalDeviceSurfaceCapabilitiesKHR ; 
 scalar_t__ vkGetPhysicalDeviceSurfaceFormatsKHR ; 
 scalar_t__ vkGetPhysicalDeviceSurfacePresentModesKHR ; 
 scalar_t__ vkGetPhysicalDeviceSurfaceSupportKHR ; 

__attribute__((used)) static void glad_vk_load_VK_KHR_surface( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_surface) return;
    vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) load("vkDestroySurfaceKHR", userptr);
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) load("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", userptr);
    vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) load("vkGetPhysicalDeviceSurfaceFormatsKHR", userptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) load("vkGetPhysicalDeviceSurfacePresentModesKHR", userptr);
    vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) load("vkGetPhysicalDeviceSurfaceSupportKHR", userptr);
}