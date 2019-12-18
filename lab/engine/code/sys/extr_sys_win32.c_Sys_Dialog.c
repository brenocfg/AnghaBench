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
typedef  int dialogType_t ;
typedef  int /*<<< orphan*/  dialogResult_t ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  DR_CANCEL ; 
 int /*<<< orphan*/  DR_NO ; 
 int /*<<< orphan*/  DR_OK ; 
 int /*<<< orphan*/  DR_YES ; 
#define  DT_ERROR 136 
#define  DT_INFO 135 
#define  DT_OK_CANCEL 134 
#define  DT_WARNING 133 
#define  DT_YES_NO 132 
#define  IDCANCEL 131 
#define  IDNO 130 
#define  IDOK 129 
#define  IDYES 128 
 int MB_ICONERROR ; 
 int MB_ICONINFORMATION ; 
 int MB_ICONQUESTION ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int MB_OKCANCEL ; 
 int MB_YESNO ; 
 int MessageBox (int /*<<< orphan*/ *,char const*,char const*,int) ; 

dialogResult_t Sys_Dialog( dialogType_t type, const char *message, const char *title )
{
	UINT uType;

	switch( type )
	{
		default:
		case DT_INFO:      uType = MB_ICONINFORMATION|MB_OK; break;
		case DT_WARNING:   uType = MB_ICONWARNING|MB_OK; break;
		case DT_ERROR:     uType = MB_ICONERROR|MB_OK; break;
		case DT_YES_NO:    uType = MB_ICONQUESTION|MB_YESNO; break;
		case DT_OK_CANCEL: uType = MB_ICONWARNING|MB_OKCANCEL; break;
	}

	switch( MessageBox( NULL, message, title, uType ) )
	{
		default:
		case IDOK:      return DR_OK;
		case IDCANCEL:  return DR_CANCEL;
		case IDYES:     return DR_YES;
		case IDNO:      return DR_NO;
	}
}