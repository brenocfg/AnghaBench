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

/* Variables and functions */
#define  R_CURSOR 136 
#define  R_FIRST 135 
#define  R_IAFTER 134 
#define  R_IBEFORE 133 
#define  R_LAST 132 
#define  R_NEXT 131 
#define  R_NOOVERWRITE 130 
#define  R_PREV 129 
#define  R_SETCURSOR 128 

__attribute__((used)) static const char *
sflags(int xflags)
{
	switch (xflags) {
	case R_CURSOR:		return "R_CURSOR";
	case R_FIRST:		return "R_FIRST";
	case R_IAFTER:		return "R_IAFTER";
	case R_IBEFORE:		return "R_IBEFORE";
	case R_LAST:		return "R_LAST";
	case R_NEXT:		return "R_NEXT";
	case R_NOOVERWRITE:	return "R_NOOVERWRITE";
	case R_PREV:		return "R_PREV";
	case R_SETCURSOR:	return "R_SETCURSOR";
	}

	return "UNKNOWN!";
}