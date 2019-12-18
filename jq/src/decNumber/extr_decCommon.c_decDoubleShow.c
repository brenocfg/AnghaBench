#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* bytes; } ;
typedef  TYPE_1__ decFloat ;
typedef  int Int ;

/* Variables and functions */
 int DECBYTES ; 
 int DECSTRING ; 
 int /*<<< orphan*/  decFloatToString (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void decFloatShow(const decFloat *df, const char *tag) {
  char hexbuf[DECBYTES*2+DECBYTES/4+1]; // NB blank after every fourth
  char buff[DECSTRING];                 // for value in decimal
  Int i, j=0;

  for (i=0; i<DECBYTES; i++) {
    #if DECLITEND
      sprintf(&hexbuf[j], "%02x", df->bytes[DECBYTES-1-i]);
    #else
      sprintf(&hexbuf[j], "%02x", df->bytes[i]);
    #endif
    j+=2;
    // the next line adds blank (and terminator) after final pair, too
    if ((i+1)%4==0) {strcpy(&hexbuf[j], " "); j++;}
    }
  decFloatToString(df, buff);
  printf(">%s> %s [big-endian]  %s\n", tag, hexbuf, buff);
  return;
  }