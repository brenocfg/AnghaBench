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
typedef  scalar_t__ PFN_vkUpdateDescriptorSetWithTemplate ;
typedef  scalar_t__ PFN_vkTrimCommandPool ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceQueueFamilyProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceMemoryProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceImageFormatProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceFormatProperties2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceFeatures2 ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceExternalSemaphoreProperties ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceExternalFenceProperties ;
typedef  scalar_t__ PFN_vkGetPhysicalDeviceExternalBufferProperties ;
typedef  scalar_t__ PFN_vkGetImageSparseMemoryRequirements2 ;
typedef  scalar_t__ PFN_vkGetImageMemoryRequirements2 ;
typedef  scalar_t__ PFN_vkGetDeviceQueue2 ;
typedef  scalar_t__ PFN_vkGetDeviceGroupPeerMemoryFeatures ;
typedef  scalar_t__ PFN_vkGetDescriptorSetLayoutSupport ;
typedef  scalar_t__ PFN_vkGetBufferMemoryRequirements2 ;
typedef  scalar_t__ PFN_vkEnumeratePhysicalDeviceGroups ;
typedef  scalar_t__ PFN_vkEnumerateInstanceVersion ;
typedef  scalar_t__ PFN_vkDestroySamplerYcbcrConversion ;
typedef  scalar_t__ PFN_vkDestroyDescriptorUpdateTemplate ;
typedef  scalar_t__ PFN_vkCreateSamplerYcbcrConversion ;
typedef  scalar_t__ PFN_vkCreateDescriptorUpdateTemplate ;
typedef  scalar_t__ PFN_vkCmdSetDeviceMask ;
typedef  scalar_t__ PFN_vkCmdDispatchBase ;
typedef  scalar_t__ PFN_vkBindImageMemory2 ;
typedef  scalar_t__ PFN_vkBindBufferMemory2 ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_VK_VERSION_1_1 ; 
 scalar_t__ vkBindBufferMemory2 ; 
 scalar_t__ vkBindImageMemory2 ; 
 scalar_t__ vkCmdDispatchBase ; 
 scalar_t__ vkCmdSetDeviceMask ; 
 scalar_t__ vkCreateDescriptorUpdateTemplate ; 
 scalar_t__ vkCreateSamplerYcbcrConversion ; 
 scalar_t__ vkDestroyDescriptorUpdateTemplate ; 
 scalar_t__ vkDestroySamplerYcbcrConversion ; 
 scalar_t__ vkEnumerateInstanceVersion ; 
 scalar_t__ vkEnumeratePhysicalDeviceGroups ; 
 scalar_t__ vkGetBufferMemoryRequirements2 ; 
 scalar_t__ vkGetDescriptorSetLayoutSupport ; 
 scalar_t__ vkGetDeviceGroupPeerMemoryFeatures ; 
 scalar_t__ vkGetDeviceQueue2 ; 
 scalar_t__ vkGetImageMemoryRequirements2 ; 
 scalar_t__ vkGetImageSparseMemoryRequirements2 ; 
 scalar_t__ vkGetPhysicalDeviceExternalBufferProperties ; 
 scalar_t__ vkGetPhysicalDeviceExternalFenceProperties ; 
 scalar_t__ vkGetPhysicalDeviceExternalSemaphoreProperties ; 
 scalar_t__ vkGetPhysicalDeviceFeatures2 ; 
 scalar_t__ vkGetPhysicalDeviceFormatProperties2 ; 
 scalar_t__ vkGetPhysicalDeviceImageFormatProperties2 ; 
 scalar_t__ vkGetPhysicalDeviceMemoryProperties2 ; 
 scalar_t__ vkGetPhysicalDeviceProperties2 ; 
 scalar_t__ vkGetPhysicalDeviceQueueFamilyProperties2 ; 
 scalar_t__ vkGetPhysicalDeviceSparseImageFormatProperties2 ; 
 scalar_t__ vkTrimCommandPool ; 
 scalar_t__ vkUpdateDescriptorSetWithTemplate ; 

__attribute__((used)) static void glad_vk_load_VK_VERSION_1_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_1) return;
    vkBindBufferMemory2 = (PFN_vkBindBufferMemory2) load("vkBindBufferMemory2", userptr);
    vkBindImageMemory2 = (PFN_vkBindImageMemory2) load("vkBindImageMemory2", userptr);
    vkCmdDispatchBase = (PFN_vkCmdDispatchBase) load("vkCmdDispatchBase", userptr);
    vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask) load("vkCmdSetDeviceMask", userptr);
    vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate) load("vkCreateDescriptorUpdateTemplate", userptr);
    vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion) load("vkCreateSamplerYcbcrConversion", userptr);
    vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate) load("vkDestroyDescriptorUpdateTemplate", userptr);
    vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion) load("vkDestroySamplerYcbcrConversion", userptr);
    vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) load("vkEnumerateInstanceVersion", userptr);
    vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups) load("vkEnumeratePhysicalDeviceGroups", userptr);
    vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2) load("vkGetBufferMemoryRequirements2", userptr);
    vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport) load("vkGetDescriptorSetLayoutSupport", userptr);
    vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures) load("vkGetDeviceGroupPeerMemoryFeatures", userptr);
    vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2) load("vkGetDeviceQueue2", userptr);
    vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2) load("vkGetImageMemoryRequirements2", userptr);
    vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2) load("vkGetImageSparseMemoryRequirements2", userptr);
    vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties) load("vkGetPhysicalDeviceExternalBufferProperties", userptr);
    vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties) load("vkGetPhysicalDeviceExternalFenceProperties", userptr);
    vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties) load("vkGetPhysicalDeviceExternalSemaphoreProperties", userptr);
    vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2) load("vkGetPhysicalDeviceFeatures2", userptr);
    vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2) load("vkGetPhysicalDeviceFormatProperties2", userptr);
    vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2) load("vkGetPhysicalDeviceImageFormatProperties2", userptr);
    vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2) load("vkGetPhysicalDeviceMemoryProperties2", userptr);
    vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2) load("vkGetPhysicalDeviceProperties2", userptr);
    vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2) load("vkGetPhysicalDeviceQueueFamilyProperties2", userptr);
    vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2) load("vkGetPhysicalDeviceSparseImageFormatProperties2", userptr);
    vkTrimCommandPool = (PFN_vkTrimCommandPool) load("vkTrimCommandPool", userptr);
    vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate) load("vkUpdateDescriptorSetWithTemplate", userptr);
}