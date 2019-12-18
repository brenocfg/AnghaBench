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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,size_t,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* trx_path ; 

__attribute__((used)) static int otrx_extract_copy(FILE *trx, size_t offset, size_t length, char *out_path) {
	FILE *out;
	size_t bytes;
	uint8_t *buf;
	int err = 0;

	out = fopen(out_path, "w");
	if (!out) {
		fprintf(stderr, "Couldn't open %s\n", out_path);
		err = -EACCES;
		goto out;
	}

	buf = malloc(length);
	if (!buf) {
		fprintf(stderr, "Couldn't alloc %zu B buffer\n", length);
		err =  -ENOMEM;
		goto err_close;
	}

	fseek(trx, offset, SEEK_SET);
	bytes = fread(buf, 1, length, trx);
	if (bytes != length) {
		fprintf(stderr, "Couldn't read %zu B of data from %s\n", length, trx_path);
		err =  -ENOMEM;
		goto err_free_buf;
	};

	bytes = fwrite(buf, 1, length, out);
	if (bytes != length) {
		fprintf(stderr, "Couldn't write %zu B to %s\n", length, out_path);
		err =  -ENOMEM;
		goto err_free_buf;
	}

	printf("Extracted 0x%zx bytes into %s\n", length, out_path);

err_free_buf:
	free(buf);
err_close:
	fclose(out);
out:
	return err;
}