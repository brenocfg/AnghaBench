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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void output_hex_blob(FILE *out, const void *pBlob, int nBlob){
  int i;
  char *zBlob = (char *)pBlob;
  raw_printf(out,"X'");
  for(i=0; i<nBlob; i++){ raw_printf(out,"%02x",zBlob[i]&0xff); }
  raw_printf(out,"'");
}