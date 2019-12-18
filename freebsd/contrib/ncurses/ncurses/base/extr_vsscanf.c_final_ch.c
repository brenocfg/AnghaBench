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
typedef  int OtherType ;
typedef  int /*<<< orphan*/  ChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  cAssigned ; 
 int /*<<< orphan*/  cChar ; 
 int /*<<< orphan*/  cDouble ; 
 int /*<<< orphan*/  cError ; 
 int /*<<< orphan*/  cFloat ; 
 int /*<<< orphan*/  cInt ; 
 int /*<<< orphan*/  cLong ; 
 int /*<<< orphan*/  cPointer ; 
 int /*<<< orphan*/  cShort ; 
 int /*<<< orphan*/  cString ; 
 int /*<<< orphan*/  cUnknown ; 
#define  oLong 130 
#define  oShort 129 
#define  oUnknown 128 

__attribute__((used)) static ChunkType
final_ch(int ch, OtherType other)
{
    ChunkType result = cUnknown;

    switch (ch) {
    case 'c':
	if (other == oUnknown)
	    result = cChar;
	else
	    result = cError;
	break;
    case 'd':
    case 'i':
    case 'X':
    case 'x':
	switch (other) {
	case oUnknown:
	    result = cInt;
	    break;
	case oShort:
	    result = cShort;
	    break;
	case oLong:
	    result = cLong;
	    break;
	}
	break;
    case 'E':
    case 'e':
    case 'f':
    case 'g':
	switch (other) {
	case oUnknown:
	    result = cFloat;
	    break;
	case oShort:
	    result = cError;
	    break;
	case oLong:
	    result = cDouble;
	    break;
	}
	break;
    case 'n':
	if (other == oUnknown)
	    result = cAssigned;
	else
	    result = cError;
	break;
    case 'p':
	if (other == oUnknown)
	    result = cPointer;
	else
	    result = cError;
	break;
    case 's':
	if (other == oUnknown)
	    result = cString;
	else
	    result = cError;
	break;
    }
    return result;
}