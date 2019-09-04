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
typedef  int /*<<< orphan*/  MD_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MD ; 
 int /*<<< orphan*/  MDFinal (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDPrint (unsigned char*) ; 
 int /*<<< orphan*/  MDUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void MDFile(char *filename)
{
  FILE *file;
  MD_CTX context;
  int len;
  unsigned char buffer[1024], digest[16];

  if ((file = fopen (filename, "rb")) == NULL) {
    printf("%s can't be opened\n", filename);
  } else {
    MDInit(&context);
    while ((len = fread (buffer, 1, 1024, file)))
      MDUpdate(&context, buffer, len);
    MDFinal(digest, &context);

    fclose(file);

    printf("MD%d (%s) = ", MD, filename);
    MDPrint(digest);
    printf("\n");
  }
}