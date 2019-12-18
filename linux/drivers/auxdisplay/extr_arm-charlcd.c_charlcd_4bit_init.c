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
struct charlcd {scalar_t__ virtbase; } ;

/* Variables and functions */
 scalar_t__ CHAR_COM ; 
 int HD_CLEAR ; 
 int HD_DISPCTRL ; 
 int HD_DISPCTRL_ON ; 
 int HD_ENTRYMODE ; 
 int HD_ENTRYMODE_INCREMENT ; 
 int HD_FUNCSET ; 
 int HD_FUNCSET_2_LINES ; 
 int HD_FUNCSET_8BIT ; 
 int HD_HOME ; 
 char* UTS_RELEASE ; 
 int /*<<< orphan*/  charlcd_4bit_command (struct charlcd*,int) ; 
 int /*<<< orphan*/  charlcd_4bit_print (struct charlcd*,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void charlcd_4bit_init(struct charlcd *lcd)
{
	/* These commands cannot be checked with the busy flag */
	writel(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	msleep(5);
	writel(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	udelay(100);
	writel(HD_FUNCSET | HD_FUNCSET_8BIT, lcd->virtbase + CHAR_COM);
	udelay(100);
	/* Go to 4bit mode */
	writel(HD_FUNCSET, lcd->virtbase + CHAR_COM);
	udelay(100);
	/*
	 * 4bit mode, 2 lines, 5x8 font, after this the number of lines
	 * and the font cannot be changed until the next initialization sequence
	 */
	charlcd_4bit_command(lcd, HD_FUNCSET | HD_FUNCSET_2_LINES);
	charlcd_4bit_command(lcd, HD_DISPCTRL | HD_DISPCTRL_ON);
	charlcd_4bit_command(lcd, HD_ENTRYMODE | HD_ENTRYMODE_INCREMENT);
	charlcd_4bit_command(lcd, HD_CLEAR);
	charlcd_4bit_command(lcd, HD_HOME);
	/* Put something useful in the display */
	charlcd_4bit_print(lcd, 0, "ARM Linux");
	charlcd_4bit_print(lcd, 1, UTS_RELEASE);
}