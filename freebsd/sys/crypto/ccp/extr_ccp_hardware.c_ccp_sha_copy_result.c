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
struct SHA_Defn {int version; TYPE_1__* axf; } ;
typedef  enum sha_version { ____Placeholder_sha_version } sha_version ;
struct TYPE_2__ {scalar_t__ hashsize; } ;

/* Variables and functions */
 scalar_t__ LSB_ENTRY_SIZE ; 
#define  SHA1 132 
#define  SHA2_224 131 
#define  SHA2_256 130 
#define  SHA2_384 129 
#define  SHA2_512 128 
 struct SHA_Defn* SHA_definitions ; 
 int /*<<< orphan*/  XXX ; 
 int /*<<< orphan*/  byteswap256 (void*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 size_t nitems (struct SHA_Defn*) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

__attribute__((used)) static void
ccp_sha_copy_result(char *output, char *buffer, enum sha_version version)
{
	const struct SHA_Defn *defn;
	size_t i;

	for (i = 0; i < nitems(SHA_definitions); i++)
		if (SHA_definitions[i].version == version)
			break;
	if (i == nitems(SHA_definitions))
		panic("bogus sha version auth_mode %u\n", (unsigned)version);

	defn = &SHA_definitions[i];

	/* Swap 256bit manually -- DMA engine can, but with limitations */
	byteswap256((void *)buffer);
	if (defn->axf->hashsize > LSB_ENTRY_SIZE)
		byteswap256((void *)(buffer + LSB_ENTRY_SIZE));

	switch (defn->version) {
	case SHA1:
		memcpy(output, buffer + 12, defn->axf->hashsize);
		break;
#if 0
	case SHA2_224:
		memcpy(output, buffer + XXX, defn->axf->hashsize);
		break;
#endif
	case SHA2_256:
		memcpy(output, buffer, defn->axf->hashsize);
		break;
	case SHA2_384:
		memcpy(output,
		    buffer + LSB_ENTRY_SIZE * 3 - defn->axf->hashsize,
		    defn->axf->hashsize - LSB_ENTRY_SIZE);
		memcpy(output + defn->axf->hashsize - LSB_ENTRY_SIZE, buffer,
		    LSB_ENTRY_SIZE);
		break;
	case SHA2_512:
		memcpy(output, buffer + LSB_ENTRY_SIZE, LSB_ENTRY_SIZE);
		memcpy(output + LSB_ENTRY_SIZE, buffer, LSB_ENTRY_SIZE);
		break;
	}
}