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
struct tuple_callbacks {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAR ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  FUNCE ; 
 int /*<<< orphan*/  FUNCID ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  INDIRECT ; 
 int /*<<< orphan*/  LINKTARGET ; 
 int /*<<< orphan*/  LONGLINK_A ; 
 int /*<<< orphan*/  LONGLINK_C ; 
 int /*<<< orphan*/  LONGLINK_CB ; 
 int /*<<< orphan*/  LONGLINK_MFC ; 
 struct tuple_callbacks MAKETUPLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANFID ; 
 int /*<<< orphan*/  VERS_1 ; 
 int /*<<< orphan*/  bar ; 
 int cardbus_parse_cis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuple_callbacks*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  funce ; 
 int /*<<< orphan*/  funcid ; 
 int /*<<< orphan*/  generic ; 
 int /*<<< orphan*/  linktarget ; 
 int /*<<< orphan*/  manfid ; 
 int /*<<< orphan*/  unhandled ; 
 int /*<<< orphan*/  vers_1 ; 

int
cardbus_do_cis(device_t cbdev, device_t child)
{
	struct tuple_callbacks init_callbacks[] = {
		MAKETUPLE(LONGLINK_CB,		unhandled),
		MAKETUPLE(INDIRECT,		unhandled),
		MAKETUPLE(LONGLINK_MFC,		unhandled),
		MAKETUPLE(BAR,			bar),
		MAKETUPLE(LONGLINK_A,		unhandled),
		MAKETUPLE(LONGLINK_C,		unhandled),
		MAKETUPLE(LINKTARGET,		linktarget),
		MAKETUPLE(VERS_1,		vers_1),
		MAKETUPLE(MANFID,		manfid),
		MAKETUPLE(FUNCID,		funcid),
		MAKETUPLE(FUNCE,		funce),
		MAKETUPLE(END,			end),
		MAKETUPLE(GENERIC,		generic),
	};

	return (cardbus_parse_cis(cbdev, child, init_callbacks, NULL));
}