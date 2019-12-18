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
 int KERNEL_SIZE ; 
 int KERNEL_START ; 
 int /*<<< orphan*/  SEEK_END ; 
 char* app_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

unsigned char* read_kernel(unsigned char* img, const char *fname)
{
  FILE *fp;
  int size;
  int i;

  for (i=KERNEL_START; i<KERNEL_START+KERNEL_SIZE; i++)
    img[i] = 0xff;

  fp = fopen(fname, "rb");
  if (fp == NULL) {
    perror(app_name);
    exit(-1);
  }

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  
  if (size > KERNEL_SIZE) {
    fprintf(stderr, "%s: kernel binary file is too big\n", app_name);
    fclose(fp);
    exit(-1);
  }

  rewind(fp);

  if (fread(img+KERNEL_START, 1, size, fp) != size) {
    fprintf(stderr, "%s: can't read kernel file\n", app_name);
    fclose(fp);
    exit(-1);
  }

  fclose(fp);
  return img;
}