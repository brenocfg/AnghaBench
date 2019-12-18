#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptr_t ;
struct TYPE_4__ {char* name; int /*<<< orphan*/ * long_name; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/ * long_name; } ;

/* Variables and functions */
 void* CSAVS (int,int,char*) ; 
 size_t T_DC ; 
 size_t T_DO ; 
 size_t T_IC ; 
 size_t T_LE ; 
 size_t T_RI ; 
 size_t T_UP ; 
 size_t T_al ; 
 size_t T_am ; 
 size_t T_at7 ; 
 size_t T_bl ; 
 size_t T_cd ; 
 size_t T_ce ; 
 size_t T_ch ; 
 size_t T_cl ; 
 size_t T_co ; 
 size_t T_dc ; 
 size_t T_dl ; 
 size_t T_dm ; 
 size_t T_ed ; 
 size_t T_ei ; 
 size_t T_fs ; 
 size_t T_ho ; 
 size_t T_ic ; 
 size_t T_im ; 
 size_t T_ip ; 
 size_t T_kd ; 
 size_t T_kh ; 
 size_t T_kl ; 
 size_t T_km ; 
 size_t T_kr ; 
 size_t T_ku ; 
 size_t T_li ; 
 size_t T_md ; 
 size_t T_me ; 
 size_t T_mr ; 
 size_t T_nd ; 
 size_t T_pt ; 
 size_t T_se ; 
 size_t T_so ; 
 int T_str ; 
 size_t T_ts ; 
 size_t T_ue ; 
 size_t T_up ; 
 size_t T_us ; 
 int T_val ; 
 size_t T_vb ; 
 size_t T_xn ; 
 TYPE_2__* tstr ; 
 TYPE_1__* tval ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void
terminit(void)
{
#ifdef NLS_CATALOGS
    int i;

    for (i = 0; i < T_str + 1; i++)
	xfree((ptr_t)(intptr_t)tstr[i].long_name);

    for (i = 0; i < T_val + 1; i++)
	xfree((ptr_t)(intptr_t)tval[i].long_name);
#endif

    tstr[T_al].name = "al";
    tstr[T_al].long_name = CSAVS(4, 1, "add new blank line");

    tstr[T_bl].name = "bl";
    tstr[T_bl].long_name = CSAVS(4, 2, "audible bell");

    tstr[T_cd].name = "cd";
    tstr[T_cd].long_name = CSAVS(4, 3, "clear to bottom");

    tstr[T_ce].name = "ce";
    tstr[T_ce].long_name = CSAVS(4, 4, "clear to end of line");

    tstr[T_ch].name = "ch";
    tstr[T_ch].long_name = CSAVS(4, 5, "cursor to horiz pos");

    tstr[T_cl].name = "cl";
    tstr[T_cl].long_name = CSAVS(4, 6, "clear screen");

    tstr[T_dc].name = "dc";
    tstr[T_dc].long_name = CSAVS(4, 7, "delete a character");

    tstr[T_dl].name = "dl";
    tstr[T_dl].long_name = CSAVS(4, 8, "delete a line");

    tstr[T_dm].name = "dm";
    tstr[T_dm].long_name = CSAVS(4, 9, "start delete mode");

    tstr[T_ed].name = "ed";
    tstr[T_ed].long_name = CSAVS(4, 10, "end delete mode");

    tstr[T_ei].name = "ei";
    tstr[T_ei].long_name = CSAVS(4, 11, "end insert mode");

    tstr[T_fs].name = "fs";
    tstr[T_fs].long_name = CSAVS(4, 12, "cursor from status line");

    tstr[T_ho].name = "ho";
    tstr[T_ho].long_name = CSAVS(4, 13, "home cursor");

    tstr[T_ic].name = "ic";
    tstr[T_ic].long_name = CSAVS(4, 14, "insert character");

    tstr[T_im].name = "im";
    tstr[T_im].long_name = CSAVS(4, 15, "start insert mode");

    tstr[T_ip].name = "ip";
    tstr[T_ip].long_name = CSAVS(4, 16, "insert padding");

    tstr[T_kd].name = "kd";
    tstr[T_kd].long_name = CSAVS(4, 17, "sends cursor down");

    tstr[T_kl].name = "kl";
    tstr[T_kl].long_name = CSAVS(4, 18, "sends cursor left");

    tstr[T_kr].name = "kr";
    tstr[T_kr].long_name = CSAVS(4, 19, "sends cursor right");

    tstr[T_ku].name = "ku";
    tstr[T_ku].long_name = CSAVS(4, 20, "sends cursor up");

    tstr[T_md].name = "md";
    tstr[T_md].long_name = CSAVS(4, 21, "begin bold");

    tstr[T_me].name = "me";
    tstr[T_me].long_name = CSAVS(4, 22, "end attributes");

    tstr[T_nd].name = "nd";
    tstr[T_nd].long_name = CSAVS(4, 23, "non destructive space");

    tstr[T_se].name = "se";
    tstr[T_se].long_name = CSAVS(4, 24, "end standout");

    tstr[T_so].name = "so";
    tstr[T_so].long_name = CSAVS(4, 25, "begin standout");

    tstr[T_ts].name = "ts";
    tstr[T_ts].long_name = CSAVS(4, 26, "cursor to status line");

    tstr[T_up].name = "up";
    tstr[T_up].long_name = CSAVS(4, 27, "cursor up one");

    tstr[T_us].name = "us";
    tstr[T_us].long_name = CSAVS(4, 28, "begin underline");

    tstr[T_ue].name = "ue";
    tstr[T_ue].long_name = CSAVS(4, 29, "end underline");

    tstr[T_vb].name = "vb";
    tstr[T_vb].long_name = CSAVS(4, 30, "visible bell");

    tstr[T_DC].name = "DC";
    tstr[T_DC].long_name = CSAVS(4, 31, "delete multiple chars");

    tstr[T_DO].name = "DO";
    tstr[T_DO].long_name = CSAVS(4, 32, "cursor down multiple");

    tstr[T_IC].name = "IC";
    tstr[T_IC].long_name = CSAVS(4, 33, "insert multiple chars");

    tstr[T_LE].name = "LE";
    tstr[T_LE].long_name = CSAVS(4, 34, "cursor left multiple");

    tstr[T_RI].name = "RI";
    tstr[T_RI].long_name = CSAVS(4, 35, "cursor right multiple");

    tstr[T_UP].name = "UP";
    tstr[T_UP].long_name = CSAVS(4, 36, "cursor up multiple");

    tstr[T_kh].name = "kh";
    tstr[T_kh].long_name = CSAVS(4, 43, "send cursor home");

    tstr[T_at7].name = "@7";
    tstr[T_at7].long_name = CSAVS(4, 44, "send cursor end");

    tstr[T_mr].name = "mr";
    tstr[T_mr].long_name = CSAVS(4, 45, "begin reverse video");

    tstr[T_str].name = NULL;
    tstr[T_str].long_name = NULL;


    tval[T_am].name = "am";
    tval[T_am].long_name = CSAVS(4, 37, "Has automatic margins");

    tval[T_pt].name = "pt";
    tval[T_pt].long_name = CSAVS(4, 38, "Can use physical tabs");

    tval[T_li].name = "li";
    tval[T_li].long_name = CSAVS(4, 39, "Number of lines");

    tval[T_co].name = "co";
    tval[T_co].long_name = CSAVS(4, 40, "Number of columns");

    tval[T_km].name = "km";
    tval[T_km].long_name = CSAVS(4, 41, "Has meta key");

    tval[T_xn].name = "xn";
    tval[T_xn].long_name = CSAVS(4, 42, "Newline ignored at right margin");

    tval[T_val].name = NULL;
    tval[T_val].long_name = NULL;
}