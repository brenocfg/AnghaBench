#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* OpenProtocol ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;
typedef  int /*<<< orphan*/  EFI_GUID ;

/* Variables and functions */
 TYPE_1__* BS ; 
 int /*<<< orphan*/  EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL ; 
 int /*<<< orphan*/  IH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EFI_STATUS
OpenProtocolByHandle(EFI_HANDLE handle, EFI_GUID *protocol, void **interface)
{
	return (BS->OpenProtocol(handle, protocol, interface, IH, NULL,
	    EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL));
}