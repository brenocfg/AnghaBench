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
typedef  int /*<<< orphan*/  OtherType ;

/* Variables and functions */
 int /*<<< orphan*/  oLong ; 
 int /*<<< orphan*/  oShort ; 
 int /*<<< orphan*/  oUnknown ; 

__attribute__((used)) static OtherType
other_ch(int ch)
{
    OtherType result = oUnknown;
    switch (ch) {
    case 'h':
	result = oShort;
	break;
    case 'l':
	result = oLong;
	break;
    }
    return result;
}