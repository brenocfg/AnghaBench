#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {void* size; int /*<<< orphan*/  metasize; scalar_t__ reserved; void* magic; } ;
typedef  TYPE_1__ seamahdr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t SEAMA_MAGIC ; 
 size_t fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 void* htonl (size_t) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  verbose (char*,int) ; 

__attribute__((used)) static size_t write_seama_header(FILE * fh, char * meta[], size_t msize, size_t size)
{
	seamahdr_t shdr;
	size_t i;
	uint16_t metasize = 0;

	/* Calculate the META size */
	for (i=0; i<msize; i++) metasize += (strlen(meta[i]) + 1);
	//+++ let meta data end on 4 alignment by siyou. 2010/3/1 03:58pm
	metasize = ((metasize+3)/4)*4;
	verbose("SEAMA META : %d bytes\n", metasize);

	/* Fill up the header, all the data endian should be network byte order. */
	shdr.magic		= htonl(SEAMA_MAGIC);
	shdr.reserved	= 0;
	shdr.metasize	= htons(metasize);
	shdr.size		= htonl(size);

	/* Write the header */
	return fwrite(&shdr, sizeof(seamahdr_t), 1, fh);
}