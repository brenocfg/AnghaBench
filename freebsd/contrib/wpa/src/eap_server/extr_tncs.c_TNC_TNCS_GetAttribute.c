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
typedef  int /*<<< orphan*/  TNC_UInt32 ;
typedef  int /*<<< orphan*/  TNC_Result ;
typedef  int /*<<< orphan*/  TNC_IMVID ;
typedef  int /*<<< orphan*/  TNC_ConnectionID ;
typedef  int /*<<< orphan*/  TNC_BufferReference ;
typedef  int /*<<< orphan*/  TNC_AttributeID ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TNC_RESULT_SUCCESS ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static TNC_Result TNC_TNCS_GetAttribute(
	TNC_IMVID imvID,
	TNC_ConnectionID connectionID,
	TNC_AttributeID attribureID,
	TNC_UInt32 bufferLength,
	TNC_BufferReference buffer,
	TNC_UInt32 *pOutValueLength)
{
	wpa_printf(MSG_DEBUG, "TNC: TNC_TNCS_GetAttribute");
	/* TODO */
	return TNC_RESULT_SUCCESS;
}