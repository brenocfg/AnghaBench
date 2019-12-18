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
typedef  scalar_t__ PFN_vkDestroyDebugReportCallbackEXT ;
typedef  scalar_t__ PFN_vkDebugReportMessageEXT ;
typedef  scalar_t__ PFN_vkCreateDebugReportCallbackEXT ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_VK_EXT_debug_report ; 
 scalar_t__ vkCreateDebugReportCallbackEXT ; 
 scalar_t__ vkDebugReportMessageEXT ; 
 scalar_t__ vkDestroyDebugReportCallbackEXT ; 

__attribute__((used)) static void glad_vk_load_VK_EXT_debug_report( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_debug_report) return;
    vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) load("vkCreateDebugReportCallbackEXT", userptr);
    vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT) load("vkDebugReportMessageEXT", userptr);
    vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) load("vkDestroyDebugReportCallbackEXT", userptr);
}