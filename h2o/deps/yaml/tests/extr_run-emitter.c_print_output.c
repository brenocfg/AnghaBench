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
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

int print_output(char *name, unsigned char *buffer, size_t size, int count)
{
    FILE *file;
    char data[BUFFER_SIZE];
    size_t data_size = 1;
    size_t total_size = 0;
    if (count >= 0) {
        printf("FAILED (at the event #%d)\nSOURCE:\n", count+1);
    }
    file = fopen(name, "rb");
    assert(file);
    while (data_size > 0) {
        data_size = fread(data, 1, BUFFER_SIZE, file);
        assert(!ferror(file));
        if (!data_size) break;
        assert(fwrite(data, 1, data_size, stdout) == data_size);
        total_size += data_size;
        if (feof(file)) break;
    }
    fclose(file);
    printf("#### (length: %d)\n", total_size);
    printf("OUTPUT:\n%s#### (length: %d)\n", buffer, size);
    return 0;
}