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
 int IMG_SIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 char* app_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

unsigned char* read_img(const char *fname)
{
  FILE *fp;
  int size;
  unsigned char *img;

  fp = fopen(fname, "rb");
  if (fp == NULL) {
    perror(app_name);
    exit(-1);
  }

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  
  if (size != IMG_SIZE) {
    fprintf(stderr, "%s: image file has wrong size\n", app_name);
    fclose(fp);
    exit(-1);
  }

  rewind(fp);

  img = malloc(IMG_SIZE);
  if (img == NULL) {
    perror(app_name);
    fclose(fp);
    exit(-1);
  }

  if (fread(img, 1, IMG_SIZE, fp) != IMG_SIZE) {
    fprintf(stderr, "%s: can't read image file\n", app_name);
    fclose(fp);
    exit(-1);
  }

  fclose(fp);
  return img;
}