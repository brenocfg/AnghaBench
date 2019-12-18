#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct access {int have; TYPE_1__* list; } ;
typedef  int off_t ;
struct TYPE_2__ {int out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHUNK ; 
 int /*<<< orphan*/  SPAN ; 
#define  Z_DATA_ERROR 130 
#define  Z_ERRNO 129 
#define  Z_MEM_ERROR 128 
 int build_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct access**) ; 
 int extract (int /*<<< orphan*/ *,struct access*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_index (struct access*) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
    int len;
    off_t offset;
    FILE *in;
    struct access *index = NULL;
    unsigned char buf[CHUNK];

    /* open input file */
    if (argc != 2) {
        fprintf(stderr, "usage: zran file.gz\n");
        return 1;
    }
    in = fopen(argv[1], "rb");
    if (in == NULL) {
        fprintf(stderr, "zran: could not open %s for reading\n", argv[1]);
        return 1;
    }

    /* build index */
    len = build_index(in, SPAN, &index);
    if (len < 0) {
        fclose(in);
        switch (len) {
        case Z_MEM_ERROR:
            fprintf(stderr, "zran: out of memory\n");
            break;
        case Z_DATA_ERROR:
            fprintf(stderr, "zran: compressed data error in %s\n", argv[1]);
            break;
        case Z_ERRNO:
            fprintf(stderr, "zran: read error on %s\n", argv[1]);
            break;
        default:
            fprintf(stderr, "zran: error %d while building index\n", len);
        }
        return 1;
    }
    fprintf(stderr, "zran: built index with %d access points\n", len);

    /* use index by reading some bytes from an arbitrary offset */
    offset = (index->list[index->have - 1].out << 1) / 3;
    len = extract(in, index, offset, buf, CHUNK);
    if (len < 0)
        fprintf(stderr, "zran: extraction failed: %s error\n",
                len == Z_MEM_ERROR ? "out of memory" : "input corrupted");
    else {
        fwrite(buf, 1, len, stdout);
        fprintf(stderr, "zran: extracted %d bytes at %llu\n", len, offset);
    }

    /* clean up and exit */
    free_index(index);
    fclose(in);
    return 0;
}