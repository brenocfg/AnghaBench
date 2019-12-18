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
struct nsp_img_hdr_sections {scalar_t__ type; unsigned int offset; unsigned int total_size; char* name; } ;
struct nsp_img_hdr_section_info {int num_sects; unsigned int sections_offset; int sect_size; } ;
struct nsp_img_hdr_head {scalar_t__ magic; unsigned int sect_info_offset; } ;
struct mtd_partition {int dummy; } ;
struct mtd_info {unsigned int size; } ;

/* Variables and functions */
 int MAX_NUM_PARTITIONS ; 
 scalar_t__ NSP_IMG_MAGIC_NUMBER ; 
 scalar_t__ NSP_IMG_SECTION_TYPE_FILESYSTEM_ROOT ; 
 scalar_t__ NSP_IMG_SECTION_TYPE_KERNEL ; 
 int /*<<< orphan*/  mtd_read (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  titan_add_partition (char*,unsigned int,unsigned int) ; 
 scalar_t__ titan_get_single_image (char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  titan_parse_env_address (char*,unsigned int*,unsigned int*) ; 
 struct mtd_partition* titan_parts ; 

int create_titan_partitions(struct mtd_info *master,
	struct mtd_partition **pparts,
	unsigned long origin)
{
	struct nsp_img_hdr_head		hdr;
	struct nsp_img_hdr_section_info	sect_info;
	struct nsp_img_hdr_sections	section;
	unsigned int			flash_base, flash_end;
	unsigned int			start, end;
	char				*name;
	int	i;
	int	total_sects=0;
	size_t len;

	/* Get the bootcfg env variable first */
	if(titan_get_single_image("BOOTCFG", &flash_base, &flash_end)) {
		/* Error, fallback */
		return -1;
	}

	/* Get access to the header, and do some validation checks */
	//hdr=(struct nsp_img_hdr_head*)flash_base;
	mtd_read(master, flash_base, sizeof(struct nsp_img_hdr_head), &len, (uint8_t *)&hdr);
	if(hdr.magic != NSP_IMG_MAGIC_NUMBER)
		return -1;	/* Not a single image */

	mtd_read(master, flash_base + hdr.sect_info_offset, sizeof(struct nsp_img_hdr_section_info), &len, (uint8_t *)&sect_info);

	/* Look for the root fs, and add it first. This way we KNOW where the rootfs is */
	for(i=0; i< sect_info.num_sects && i<MAX_NUM_PARTITIONS; i++){
		mtd_read(master, flash_base + sect_info.sections_offset + (i * sect_info.sect_size) , sizeof(struct nsp_img_hdr_sections), &len, (uint8_t *)&section);
		/* Add only the root partition */
		if(section.type != NSP_IMG_SECTION_TYPE_FILESYSTEM_ROOT){
			continue;
		}
		start=flash_base + section.offset;
		end=start + section.total_size;
		titan_add_partition("root", start, end);
		total_sects++;
		
	}

	for(i=0; i< sect_info.num_sects && i<MAX_NUM_PARTITIONS; i++){

		mtd_read(master, flash_base + sect_info.sections_offset + (i * sect_info.sect_size) , sizeof(struct nsp_img_hdr_sections), &len, (uint8_t *)&section);

		name=section.name;
		if(section.type == NSP_IMG_SECTION_TYPE_FILESYSTEM_ROOT)
		{
			name = "rootfs";
			start=flash_base + section.offset;
			end=flash_end;
			titan_add_partition(name, start, end);
			total_sects++;
		}
		else if(section.type == NSP_IMG_SECTION_TYPE_KERNEL)
		{
			name = "kernel";
			start=flash_base + section.offset;
			end=start + section.total_size;
			titan_add_partition(name, start, end);
			total_sects++;
		}

	}

	/* Next, lets add the single image */
	titan_add_partition("primary_image", flash_base, flash_end);
	total_sects++;


	titan_add_partition("full_image", 0,  master->size);
	total_sects++;

	if (!titan_parse_env_address("BOOTLOADER", &start, &end)){
		titan_add_partition("bootloader", start, end);
		total_sects++;
	}
	if (!titan_parse_env_address("boot_env", &start, &end)){
		titan_add_partition("boot_env", start, end);
		total_sects++;
	}
	*pparts = titan_parts;
	return total_sects;
}