#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ magic; int /*<<< orphan*/  metasize; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  shdr ;
typedef  TYPE_1__ seamahdr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_SEAMA_META_SIZE ; 
 int /*<<< orphan*/  SEAMA_MAGIC ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (TYPE_1__*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ match_meta (char const*,size_t) ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 char** o_images ; 
 size_t o_isize ; 
 scalar_t__ o_msize ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verify_seama (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extract_file(const char * output)
{
	FILE * ifh = NULL;
	FILE * ofh = NULL;
	size_t msize, isize, i, m;
	seamahdr_t shdr;
	uint8_t buf[MAX_SEAMA_META_SIZE];
	int done = 0;

	/* We need meta for searching the target image. */
	if (o_msize == 0)
	{
		printf("SEAMA: need meta for searching image.\n");
		return;
	}

	/* Walk through each input file */
	for (i = 0; i < o_isize; i++)
	{
		/* verify the input file */
		if (verify_seama(o_images[i], 0) < 0)
		{
			printf("SEAMA: '%s' is not a seama file !\n", o_images[i]);
			continue;
		}
		/* open the input file */
		ifh  = fopen(o_images[i], "r");
		if (!ifh) continue;
		/* read file */
		while (!feof(ifh) && !ferror(ifh))
		{
			/* read header */
			fread(&shdr, sizeof(shdr), 1, ifh);
			if (shdr.magic != htonl(SEAMA_MAGIC)) break;
			/* Get the size */
			isize = ntohl(shdr.size);
			msize = ntohs(shdr.metasize);
			if (isize == 0)
			{
				while (msize > 0)
				{
					m = fread(buf, sizeof(char), (msize < MAX_SEAMA_META_SIZE) ? msize : MAX_SEAMA_META_SIZE, ifh);
					if (m <= 0) break;
					msize -= m;
				}
				continue;
			}
			/* read checksum */
			fread(buf, sizeof(char), 16, ifh);
			if (msize > 0)
			{
				/* read META */
				fread(buf, sizeof(char), msize, ifh);
				if (match_meta((const char *)buf, msize))
				{
					printf("SEAMA: found image @ '%s', image size: %zu\n", o_images[i], isize);
					/* open output file */
					ofh = fopen(output, "w");
					if (!ofh) printf("SEAMA: unable to open '%s' for writting.\n",output);
					else
					{
						while (isize > 0)
						{
							m = fread(buf, sizeof(char), (isize < MAX_SEAMA_META_SIZE) ? isize : MAX_SEAMA_META_SIZE, ifh);
							if (m <= 0) break;
							fwrite(buf, sizeof(char), m, ofh);
							isize -= m;
						}
						fclose(ofh);
					}
					done++;
					break;
				}
			}
			while (isize > 0)
			{
				m = fread(buf, sizeof(char), (isize < MAX_SEAMA_META_SIZE) ? isize : MAX_SEAMA_META_SIZE, ifh);
				if (m <= 0) break;
				isize -= m;
			}
		}
		/* close the file. */
		fclose(ifh);
		if (done) break;
	}
	return;
}