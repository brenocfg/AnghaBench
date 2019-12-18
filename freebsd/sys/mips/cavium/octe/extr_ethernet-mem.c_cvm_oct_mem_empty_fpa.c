void cvm_oct_mem_empty_fpa(int pool, int size, int elements)
{
	char *memory;

	do {
		memory = cvmx_fpa_alloc(pool);
		if (memory) {
			struct mbuf *m = *(struct mbuf **)(memory - sizeof(void *));
			elements--;
			m_freem(m);
		}
	} while (memory);

	if (elements < 0)
		printf("Warning: Freeing of pool %u had too many mbufs (%d)\n", pool, elements);
	else if (elements > 0)
		printf("Warning: Freeing of pool %u is missing %d mbufs\n", pool, elements);
}